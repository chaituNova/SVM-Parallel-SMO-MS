function generateGraphsAlg2(dtst)
% Matlab script to generate 2d graphs
%clear all;clc;
%narr=[1 2 4 8 16 32 64 128];
%narr=[1];
%dtst=5;
switch dtst
    case 0
        dname='mnist';
    case 1
        dname='splice';
    case 2
        dname='notmnist';
    case 3
        dname='a9a';
    case 4
        dname='ijcnn1';
    case 5
        dname='codrna';
    case 6
        dname='covtype';
end

% for node=1:length(narr)
%     procf=[dname '_output\' dname '_n' int2str(narr(node)) '_proc.txt'];
%     bexist=exist(procf,'file');
%     if bexist == 0
%         continue
%     end
%     spdpf=[dname '_output\' dname '_n' int2str(narr(node)) '_spdp.txt'];
%     opf=[dname '_output\' dname '_n' int2str(narr(node)) '_output.fig'];
%     proc = csvread(procf);
%     spdp = csvread(spdpf);
% 
%     spdp(spdp==0)=NaN;
%     proc(proc==0)=NaN;
%     
%     figure;
%     %bar3(spdp,0.5) 
%     plot(proc,spdp,'-o');
%           
%     xlabel('Processes');
%     ylabel('Speedup');    
%     tname=[dname ' nodes ' int2str(narr(node))];
%     title(tname);
%     savefig(opf);
%     
% end

    procf=[dname '_output\' dname '_np_proc.txt'];
    bexist=exist(procf,'file');
    if bexist ~= 0
        spdpf=[dname '_output\' dname '_np_spdp.txt'];
        opf=[dname '_output\' dname '_np_output.fig'];
        nproc = csvread(procf);
        spdp = csvread(spdpf);

        spdp(spdp==0)=NaN;
        nproc(nproc==0)=NaN;

        figure;
        %bar3(spdp,0.5) 
        plot(nproc,spdp,'-o');

        xlabel('Processes');
        ylabel('Speedup');    
        tname=[dname ' nodes=processes'];
        title(tname);
        savefig(opf);
    end
end
