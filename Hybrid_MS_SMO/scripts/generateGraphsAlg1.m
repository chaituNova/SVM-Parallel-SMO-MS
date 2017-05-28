function generateGraphsAlg1(dtst)
% Matlab script to generate 3d graphs 


%clear all;clc;
narr=[1 2 4 8 16];
%narr=[1];
%dtst=2;
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



for node=1:length(narr)
    procf=[dname '_output\' dname '_n' int2str(narr(node)) '_proc.txt'];
    bexist=exist(procf,'file');
    if bexist == 0
        continue
    end
    thrdf=[dname '_output\' dname '_n' int2str(narr(node)) '_thrd.txt'];
    spdpf=[dname '_output\' dname '_n' int2str(narr(node)) '_spdp.txt'];
    opf=[dname '_output\' dname '_n' int2str(narr(node)) '_output.fig'];
    proc = csvread(procf);
    thrd = csvread(thrdf);
    spdp = csvread(spdpf);

    spdp(spdp==0)=NaN;
    proc(proc==0)=NaN;
    thrd(thrd==0)=NaN;
    figure;
    bar3(spdp,0.5) 
    set(gca,'XTickLabel',thrd(1,:))
    set(gca,'YTickLabel',proc(:,1))
    
    ylabel('Processes');
    xlabel('Threads per Process');
    zlabel('Speedup');    
    tname=[dname ' nodes ' int2str(narr(node))];
    title(tname);
    savefig(opf);
    
end

end
